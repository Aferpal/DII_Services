package orchestration.DTOs;

public class NetworkNewDTO {
    private Integer owner;
    private String name;

    public NetworkNewDTO(){}

    public Integer getOwner() {
        return owner;
    }

    public void setOwner(Integer owner) {
        this.owner = owner;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
}
