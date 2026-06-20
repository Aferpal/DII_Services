package clientapi.models;

import java.util.List;

public class Volume {
    public Integer id;
    public Integer storage_size_kbytes;
    public String name;
    public Integer owner;

    public Volume(){}

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
