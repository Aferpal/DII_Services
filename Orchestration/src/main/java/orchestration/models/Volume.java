package orchestration.models;

import jakarta.persistence.*;
import orchestration.DTOs.VolumeNewDTO;

import java.util.List;

@Entity
@Table(name = "VOLUME")
public class Volume {

    @Id @GeneratedValue(strategy = GenerationType.IDENTITY)
    public Integer id;
    public Integer storage_size_kbytes;
    public String name;
    public Integer owner;

    @ManyToMany(mappedBy = "volumes")
    private List<VM> vms;

    public Volume(){}

    public Volume(VolumeNewDTO volume_data){
        this.storage_size_kbytes = volume_data.getSize();
        this.name = volume_data.getName();
        this.owner = volume_data.getOwner();
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public Integer getStorage_size_kbytes() {
        return storage_size_kbytes;
    }

    public void setStorage_size_kbytes(Integer storage_size_kbytes) {
        this.storage_size_kbytes = storage_size_kbytes;
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
