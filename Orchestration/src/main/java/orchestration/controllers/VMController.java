package orchestration.controllers;

import orchestration.DTOs.VMDTO;
import orchestration.DTOs.VMNewDTO;
import orchestration.services.VMManagementService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/vms")
public class VMController {
    VMManagementService service;

    @Autowired
    public VMController(VMManagementService service){
        this.service = service;
    }

    @GetMapping("")
    public ResponseEntity<List<VMDTO>> getAllUserVMs(@RequestParam(name = "user") Integer user_id){
        return ResponseEntity.ok(service.getAllUserVMs(user_id));
    }

    @PostMapping("")
    public ResponseEntity<VMDTO> createExamen(@RequestBody VMNewDTO body){
        return service.createVM(body)
                .map(ResponseEntity::ok)
                .orElse(ResponseEntity.badRequest().build());
    }
}
