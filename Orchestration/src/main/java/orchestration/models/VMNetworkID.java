package orchestration.models;

import jakarta.persistence.Embeddable;
import java.util.Objects;

@Embeddable
public class VMNetworkID {
    private Integer vm_id;
    private Integer network_id;

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
