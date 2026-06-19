package orchestration.models;

import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.Id;
import jakarta.persistence.OneToMany;

import java.util.List;

@Entity
public class VM {

    @Id @GeneratedValue
    private Long id;
    private Long cpu;
    private Long memory;
    private Long owner;
    private Long hyperv;
    private Character status;

    @OneToMany(mappedBy = "vm")
    public List<VMNetwork> networks;

    public VM(){}

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public Long getCpu() {
        return cpu;
    }

    public void setCpu(Long cpu) {
        this.cpu = cpu;
    }

    public Long getMemory() {
        return memory;
    }

    public void setMemory(Long memory) {
        this.memory = memory;
    }

    public Long getOwner() {
        return owner;
    }

    public void setOwner(Long owner) {
        this.owner = owner;
    }

    public Long getHyperv() {
        return hyperv;
    }

    public void setHyperv(Long hyperv) {
        this.hyperv = hyperv;
    }

    public Character getStatus() {
        return status;
    }

    public void setStatus(Character status) {
        this.status = status;
    }
}
