package orchestration.models;

import jakarta.persistence.Embeddable;
import java.util.Objects;

@Embeddable
public class VMNetworkID {
    private Integer vm_id;
    private Integer network_id;

    public VMNetworkID(){}

    public VMNetworkID(Integer vm_id, Integer network_id) {
        this.vm_id = vm_id;
        this.network_id = network_id;
    }

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

    @Override
    public boolean equals(Object o) {
        if (o == null || getClass() != o.getClass()) return false;
        VMNetworkID that = (VMNetworkID) o;
        return Objects.equals(vm_id, that.vm_id) && Objects.equals(network_id, that.network_id);
    }

    @Override
    public int hashCode() {
        return Objects.hash(vm_id, network_id);
    }
}
