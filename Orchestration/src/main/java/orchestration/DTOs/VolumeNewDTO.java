package orchestration.DTOs;

public class VolumeNewDTO {
    private Integer owner;
    private Integer size;
    private String name;

    public VolumeNewDTO(){}

    public Integer getOwner() {
        return owner;
    }

    public void setOwner(Integer owner) {
        this.owner = owner;
    }

    public Integer getSize() {
        return size;
    }

    public void setSize(Integer size) {
        this.size = size;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
}
