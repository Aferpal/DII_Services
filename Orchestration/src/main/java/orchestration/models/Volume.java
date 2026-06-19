package orchestration.models;

import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.Id;
import jakarta.persistence.Table;

@Entity
@Table(name = "VOLUME")
public class Volume {

    @Id @GeneratedValue
    public Long id;
    public Long storage_size_kbytes;
    public String name;
    public Long owner;

    public Volume(){}

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public Long getStorage_size_kbytes() {
        return storage_size_kbytes;
    }

    public void setStorage_size_kbytes(Long storage_size_kbytes) {
        this.storage_size_kbytes = storage_size_kbytes;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Long getOwner() {
        return owner;
    }

    public void setOwner(Long owner) {
        this.owner = owner;
    }
}
