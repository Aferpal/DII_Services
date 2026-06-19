package orchestration.models;

import jakarta.persistence.*;

import java.util.List;

@Entity
@Table(name = "NETWORK")
public class Network {

    @Id @GeneratedValue
    public Long id;
    public String name;
    public Long owner;

    @OneToMany(mappedBy = "network_id")
    public List<VMNetwork> vms;

    public Network(){}

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
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
