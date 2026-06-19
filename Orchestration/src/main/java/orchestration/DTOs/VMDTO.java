package orchestration.DTOs;

import orchestration.models.VM;

public class VMDTO {
    private Integer id;
    private Integer owner;
    private Integer cpu;
    private Integer memory;

    public VMDTO(){}

    public VMDTO(Integer id, Integer owner, Integer CPU, Integer memory) {
        this.id = id;
        this.owner = owner;
        this.cpu = CPU;
        this.memory = memory;
    }

    public static VMDTO of(VM vm){
        return new VMDTO(vm.getId(), vm.getOwner(), vm.getCpu(), vm.getMemory());
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public Integer getOwner() {
        return owner;
    }

    public void setOwner(Integer owner) {
        this.owner = owner;
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
}
