package orchestration.DTOs;

import orchestration.models.Network;

public class NetworkDTO {
    private Integer id;
    private String name;
    private Integer owner;

    public NetworkDTO(){}

    public NetworkDTO(Integer id, String name, Integer owner) {
        this.id = id;
        this.name = name;
        this.owner = owner;
    }

    public static NetworkDTO of (Network network){
        return new NetworkDTO(network.getId(), network.getName(), network.getOwner());
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Integer getOwner() {
        return owner;
    }

    public void setOwner(Integer owner) {
        this.owner = owner;
    }
}
