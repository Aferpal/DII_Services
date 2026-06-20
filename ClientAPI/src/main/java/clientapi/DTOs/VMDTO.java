package clientapi.DTOs;

import clientapi.models.Volume;
import com.fasterxml.jackson.annotation.JsonPropertyOrder;

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
