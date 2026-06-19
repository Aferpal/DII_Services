package orchestration.models;

import jakarta.persistence.Embeddable;

@Embeddable
public class VMNetworkdID {
    private Integer vm_id;
    private Integer network_id;
}
