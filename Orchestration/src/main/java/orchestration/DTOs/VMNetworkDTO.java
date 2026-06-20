package orchestration.DTOs;

public class VMNetworkDTO {
    private Integer vm_id;
    private Integer network_id;
    private Integer owner;

    public VMNetworkDTO(){}

    public Integer getVm_id() {
        return vm_id;
    }

    public void setVm_id(Integer vm_id) {
        this.vm_id = vm_id;
    }

    public Integer getNetwork_id() {
        return network_id;
    }

    public void setNetwork_id(Integer network_id) {
        this.network_id = network_id;
    }

    public Integer getOwner() {
        return owner;
    }

    public void setOwner(Integer owner) {
        this.owner = owner;
    }
}
