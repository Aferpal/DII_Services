package orchestration.DTOs;

public class VMVolumeDTO {
    private Integer vm_id;
    private Integer volume_id;
    private Integer owner;

    public VMVolumeDTO(){}

    public Integer getVolume_id() {
        return volume_id;
    }

    public void setVolume_id(Integer volume_id) {
        this.volume_id = volume_id;
    }

    public Integer getVm_id() {
        return vm_id;
    }

    public void setVm_id(Integer vm_id) {
        this.vm_id = vm_id;
    }

    public Integer getOwner() {
        return owner;
    }

    public void setOwner(Integer owner) {
        this.owner = owner;
    }
}
