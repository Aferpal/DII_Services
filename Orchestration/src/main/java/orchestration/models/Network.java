package orchestration.models;

import jakarta.persistence.*;

import java.util.List;

@Entity
@Table(name = "NETWORK")
public class Network {

    @Id @GeneratedValue(strategy = GenerationType.IDENTITY)
    public Integer id;
    public String name;
    public Integer owner;

    @OneToMany(mappedBy = "network_id")
    public List<VMNetwork> vms;

    public Network(){}

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
