package orchestration.models;

import jakarta.persistence.Embeddable;

@Embeddable
public class VMNetworkdID {
    private Long vm_id;
    private Long network_id;
}
