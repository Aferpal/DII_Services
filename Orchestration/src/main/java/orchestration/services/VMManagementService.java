package orchestration.services;

import orchestration.models.Network;
import orchestration.models.VM;
import orchestration.models.Volume;
import orchestration.repositories.NetworkRepository;
import orchestration.repositories.VMRepository;
import orchestration.repositories.VolumeRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

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

    public List<VM> getAllUserVMs(Integer user_id){
        return vmRepository.findByOwner(user_id);
    }

    public List<Network> getAllUserNetworks(Integer user_id){
        return networkRepository.findByOwner(user_id);
    }

    public List<Volume> getAllUserVolumes(Integer user_id){
        return volumeRepository.findByOwner(user_id);
    }


}
