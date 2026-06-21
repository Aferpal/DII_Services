package orchestration.DTOs;

import com.fasterxml.jackson.annotation.JsonPropertyOrder;
import orchestration.models.VM;
import orchestration.models.VMNetwork;
import orchestration.models.Volume;

import java.util.ArrayList;
import java.util.List;

@JsonPropertyOrder({"id", "owner", "cpu", "memory", "volumes", "networks"})
public class VMDTO {
    private Integer id;
    private Integer owner;
    private Integer cpu;
    private Integer memory;
    private List<Volume> volumes;
    private List<NetAllocationDTO> networks;

    public VMDTO(){}

    public VMDTO(Integer id, Integer owner, Integer CPU, Integer memory, List<Volume> volumes, List<NetAllocationDTO> networks) {
        this.id = id;
        this.owner = owner;
        this.cpu = CPU;
        this.memory = memory;
        this.volumes = volumes;
        this.networks = networks;
    }

    public static VMDTO of(VM vm){
        vm.volumes = (vm.volumes == null) ? new ArrayList<Volume>() : vm.volumes;
        vm.networks = (vm.networks == null) ? new ArrayList<VMNetwork>() : vm.networks;

        return new VMDTO(vm.getId(), vm.getOwner(), vm.getCpu(), vm.getMemory(), vm.getVolumes(), vm.getNetworks().stream().map(NetAllocationDTO::of).toList());
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public Integer getOwner() {
        return owner;
    }

    public void setOwner(Integer owner) {
        this.owner = owner;
    }

    public Integer getCpu() {
        return cpu;
    }

    public void setCpu(Integer cpu) {
        this.cpu = cpu;
    }

    public Integer getMemory() {
        return memory;
    }

    public void setMemory(Integer memory) {
        this.memory = memory;
    }

    public List<Volume> getVolumes() {
        return volumes;
    }

    public void setVolumes(List<Volume> volumes) {
        this.volumes = volumes;
    }

    public List<NetAllocationDTO> getNetworks() {
        return networks;
    }

    public void setNetworks(List<NetAllocationDTO> networks) {
        this.networks = networks;
    }
}
