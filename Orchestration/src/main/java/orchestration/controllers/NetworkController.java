package orchestration.controllers;

import orchestration.DTOs.NetworkDTO;
import orchestration.DTOs.NetworkNewDTO;
import orchestration.services.VMManagementService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/networks")
public class NetworkController {
    VMManagementService service;

    @Autowired
    public NetworkController(VMManagementService service){
        this.service = service;
    }

    @GetMapping("")
    public ResponseEntity<List<NetworkDTO>> getAllUserNetworks(@RequestParam(name = "user") Integer user_id){
        return ResponseEntity.ok(service.getAllUserNetworks(user_id));
    }

    @PostMapping("")
    public ResponseEntity<NetworkDTO> createNetwork(@RequestBody NetworkNewDTO body){
        return service.createNetwork(body)
                .map(ResponseEntity::ok)
                .orElse(ResponseEntity.badRequest().build());
    }
}
