package orchestration.services;

import jakarta.transaction.Transactional;
import orchestration.DTOs.*;
import orchestration.exceptions.InvalidNetworkException;
import orchestration.exceptions.InvalidVMException;
import orchestration.exceptions.InvalidVolumeException;
import orchestration.exceptions.MismatchingOwnerException;
import orchestration.models.Network;
import orchestration.models.VM;
import orchestration.models.VMNetwork;
import orchestration.models.Volume;
import orchestration.repositories.NetworkRepository;
import orchestration.repositories.VMNetworkRepository;
import orchestration.repositories.VMRepository;
import orchestration.repositories.VolumeRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Optional;
import java.util.Random;

@Service
public class VMManagementService {
    VMRepository vmRepository;
    NetworkRepository networkRepository;
    VolumeRepository volumeRepository;
    VMNetworkRepository vmNetworkRepository;

    @Autowired
    public VMManagementService(VMRepository vmRepository, NetworkRepository networkRepository, VolumeRepository volumeRepository, VMNetworkRepository vmNetworkRepository){
        this.vmRepository = vmRepository;
        this.networkRepository = networkRepository;
        this.volumeRepository = volumeRepository;
        this.vmNetworkRepository = vmNetworkRepository;
    }

    public List<VMDTO> getAllUserVMs(Integer user_id){
        return vmRepository.findByOwner(user_id).stream().map(VMDTO::of).toList();
    }

    public List<NetworkDTO> getAllUserNetworks(Integer user_id){
        return networkRepository.findByOwner(user_id).stream().map(NetworkDTO::of).toList();
    }

    public List<VolumeDTO> getAllUserVolumes(Integer user_id){
        return volumeRepository.findByOwner(user_id).stream().map(VolumeDTO::of).toList();
    }

    public Optional<VMDTO> createVM(VMNewDTO vm_data){
        VM newVM = new VM(vm_data);
        Optional<VMDTO> result = Optional.of(VMDTO.of(vmRepository.save(newVM)));

        /*
        * Aquí tenemos que llamar al servicio de los hipervisores para que se lance la máquina virtual
        * Si fallase, habría que notificar al cliente, viendo si el problema ha sido nuestro o de la definición de la máquina
        */

        return result;
    }

    @Transactional
    public Optional<NetworkDTO> createNetwork(NetworkNewDTO network_data){
        Network newNetwork = new Network(network_data);
        Optional<NetworkDTO> result = Optional.of(NetworkDTO.of(networkRepository.save(newNetwork)));

        /*
        * Aquí tenemos que llamar al servicio de los hipervisores para que en efecto cree la red
        * Si fallase, lanzamos una excepción para cancelar la transacción
        */

        return result;
    }

    @Transactional
    public Optional<VolumeDTO> createVolume(VolumeNewDTO volume_data){
        Volume newVolume = new Volume(volume_data);
        Optional<VolumeDTO> result = Optional.of(VolumeDTO.of(volumeRepository.save(newVolume)));

        /*
        * Aquí tenemos que llamar al servicio del target para verdaderamente crear el volumen
        * Si fallase, lanzamos una excepción para cancelar la transacción
        */

        return result;
    }

    public Optional<VMDTO> addVolumeToVM(VMVolumeDTO allocation){
        Optional<VM> vm = vmRepository.findById(allocation.getVm_id());
        if(vm.isEmpty()){
            throw new InvalidVMException("No VM found with id: "+allocation.getVm_id());
        }

        Optional<Volume> volume = volumeRepository.findById(allocation.getVolume_id());
        if (volume.isEmpty()){
            throw new InvalidVolumeException("No volume found with id: "+allocation.getVolume_id());
        }

        if (!allocation.getOwner().equals(vm.get().getOwner()) || !allocation.getOwner().equals(volume.get().getOwner())){
            throw new MismatchingOwnerException("The VM or the volume does does not belong to specified owner");
        }
        vm.get().getVolumes().add(volume.get());
        return Optional.of(VMDTO.of(vmRepository.save(vm.get())));
    }

    public VMDTO addNetworkToVM(VMNetworkDTO allocation){
        Optional<VM> vm = vmRepository.findById(allocation.getVm_id());
        if(vm.isEmpty()){
            throw new InvalidVMException("No VM found with id: "+allocation.getVm_id());
        }

        Optional<Network> network = networkRepository.findById(allocation.getNetwork_id());
        if (network.isEmpty()){
            throw new InvalidNetworkException("No network found with id: "+allocation.getNetwork_id());
        }

        if (!allocation.getOwner().equals(vm.get().getOwner()) || !allocation.getOwner().equals(network.get().getOwner())){
            throw new MismatchingOwnerException("The VM or the volume does does not belong to specified owner");
        }

        // Generate random MAC for our connection
        Random rand = new Random();
        byte[] MAC = new byte[6];
        rand.nextBytes(MAC);

        // Ensure valid MAC
        MAC[0] = (byte) (MAC[0] | 0x02);  // Locally administered
        MAC[0] = (byte) (MAC[0] & 0xfe);  // Unicast

        StringBuilder macString = new StringBuilder();
        for (byte b : MAC){
            if (!macString.isEmpty()){
                macString.append(":");
            }
            macString.append(String.format("%02x", b));
        }

        VMNetwork relation = new VMNetwork(vm.get(), network.get(), macString.toString());
        vmNetworkRepository.save(relation);
        return VMDTO.of(vmRepository.findById(allocation.getVm_id()).get());
    }

}
