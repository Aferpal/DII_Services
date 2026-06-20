package clientapi.DTOs;

public class NetAllocationDTO {
    private String name;
    private Integer network_id;
    private String MAC;

    public NetAllocationDTO(){}

    public NetAllocationDTO(String name, Integer network_id, String MAC) {
        this.name = name;
        this.network_id = network_id;
        this.MAC = MAC;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Integer getNetwork_id() {
        return network_id;
    }

    public void setNetwork_id(Integer network_id) {
        this.network_id = network_id;
    }

    public String getMAC() {
        return MAC;
    }

    public void setMAC(String MAC) {
        this.MAC = MAC;
    }
}
