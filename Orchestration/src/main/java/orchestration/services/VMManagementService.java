package orchestration.services;

import jakarta.transaction.Transactional;
import orchestration.DTOs.*;
import orchestration.models.Network;
import orchestration.models.VM;
import orchestration.models.Volume;
import orchestration.repositories.NetworkRepository;
import orchestration.repositories.VMRepository;
import orchestration.repositories.VolumeRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Optional;

@Service
public class VMManagementService {
    VMRepository vmRepository;
    NetworkRepository networkRepository;
    VolumeRepository volumeRepository;

    @Autowired
    public VMManagementService(VMRepository vmRepository, NetworkRepository networkRepository, VolumeRepository volumeRepository){
        this.vmRepository = vmRepository;
        this.networkRepository = networkRepository;
        this.volumeRepository = volumeRepository;
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
        return Optional.of(VMDTO.of(vmRepository.save(newVM)));
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

}
