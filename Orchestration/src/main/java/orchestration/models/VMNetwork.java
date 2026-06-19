package orchestration.models;

import jakarta.persistence.*;

@Entity
@Table(name = "VM_IN_NETWORK")
public class VMNetwork {

    @EmbeddedId
    private VMNetworkID id;

    @ManyToOne
    @MapsId("vm_id")
    @JoinColumn(name = "vm_id")
    public VM vm;

    @ManyToOne
    @MapsId("network_id")
    @JoinColumn(name = "network_id")
    public Network network_id;

    public String MAC;

    public VMNetwork(){}

    public VM getVm() {
        return vm;
    }

    public void setVm(VM vm) {
        this.vm = vm;
    }

    public Network getNetwork_id() {
        return network_id;
    }

    public void setNetwork_id(Network network_id) {
        this.network_id = network_id;
    }

    public String getMAC() {
        return MAC;
    }

    public void setMAC(String MAC) {
        this.MAC = MAC;
    }
}
