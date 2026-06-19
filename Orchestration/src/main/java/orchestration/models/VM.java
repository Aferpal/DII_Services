package orchestration.models;

import jakarta.persistence.*;
import orchestration.DTOs.VMNewDTO;

import java.util.List;

@Entity
public class VM {

    @Id @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Integer id;
    private Integer cpu;
    private Integer memory;
    private Integer owner;
    private Integer hyperv;
    private Character status;

    @OneToMany(mappedBy = "vm")
    public List<VMNetwork> networks;

    @ManyToMany
    @JoinTable(name = "VM_HAS_VOLUME",
        joinColumns = @JoinColumn(name = "vm_id"),
            inverseJoinColumns = @JoinColumn(name = "volume_id")
    )
    public List<Volume> volumes;

    public VM(){}

    public VM(VMNewDTO vm_data){
        this.cpu = vm_data.getCPU();
        this.memory = vm_data.getMemory();
        this.owner = vm_data.getOwner();
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public Integer getCpu() {
        return cpu;
    }

    public void setCpu(Integer cpu) {
        this.cpu = cpu;
    }

    public Integer getMemory() {
        return memory;
    }

    public void setMemory(Integer memory) {
        this.memory = memory;
    }

    public Integer getOwner() {
        return owner;
    }

    public void setOwner(Integer owner) {
        this.owner = owner;
    }

    public Integer getHyperv() {
        return hyperv;
    }

    public void setHyperv(Integer hyperv) {
        this.hyperv = hyperv;
    }

    public Character getStatus() {
        return status;
    }

    public void setStatus(Character status) {
        this.status = status;
    }
}
