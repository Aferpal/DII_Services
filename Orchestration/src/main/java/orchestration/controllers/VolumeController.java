package orchestration.controllers;

import orchestration.DTOs.VolumeDTO;
import orchestration.DTOs.VolumeNewDTO;
import orchestration.services.VMManagementService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/volumes")
public class VolumeController {
    VMManagementService service;

    @Autowired
    public VolumeController(VMManagementService service){
        this.service = service;
    }

    @GetMapping("")
    public ResponseEntity<List<VolumeDTO>> getAllUserVolumes(@RequestParam(name = "user") Integer user_id){
        return ResponseEntity.ok(service.getAllUserVolumes(user_id));
    }

    @PostMapping("")
    public ResponseEntity<VolumeDTO> createExamen(@RequestBody VolumeNewDTO body){
        return service.createVolume(body)
                .map(ResponseEntity::ok)
                .orElse(ResponseEntity.badRequest().build());
    }
}
