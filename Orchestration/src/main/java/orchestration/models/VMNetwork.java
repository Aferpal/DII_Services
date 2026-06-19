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
    public Network network;

    public String MAC;

    public VMNetwork(){}

    public VMNetwork(VM vm, Network network, String MAC) {
        this.id = new VMNetworkID(vm.getId(), network.getId());
        this.vm = vm;
        this.network = network;
        this.MAC = MAC;
    }

    public VM getVm() {
        return vm;
    }

    public void setVm(VM vm) {
        this.vm = vm;
    }

    public Network getNetwork() {
        return network;
    }

    public void setNetwork(Network network) {
        this.network = network;
    }

    public String getMAC() {
        return MAC;
    }

    public void setMAC(String MAC) {
        this.MAC = MAC;
    }
}
