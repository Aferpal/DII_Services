package clientapi.controllers;

import clientapi.DTOs.*;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.http.MediaType;
import org.springframework.http.RequestEntity;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.client.RestTemplate;

import java.util.List;

@RestController
@RequestMapping("/vms")
public class VMController {
    RestTemplate restTemplate;

    @Value("${externalServerUrl}")
    private String baseUrl;

    @Autowired
    public VMController (RestTemplate restTemplate){
        this.restTemplate = restTemplate;
    }

    @GetMapping("")
    public ResponseEntity<VMDTO[]> getAllUserVMs(@RequestParam(name = "user") Integer user_id){
        return restTemplate.getForEntity(baseUrl+"/vms?user="+user_id, VMDTO[].class);
    }

    @PostMapping("")
    public ResponseEntity<VMDTO> createExamen(@RequestBody VMNewDTO body){
        RequestEntity<VMNewDTO> request = RequestEntity.post(baseUrl+"/vms")
                .contentType(MediaType.APPLICATION_JSON)
                .body(body);
        return restTemplate.exchange(request, VMDTO.class);
    }

    @PutMapping("addVolume")
    public ResponseEntity<VMDTO> addVolume(@RequestBody VMVolumeDTO allocation){
        RequestEntity<VMVolumeDTO> request = RequestEntity.put(baseUrl+"/vms/addVolume")
                .contentType(MediaType.APPLICATION_JSON)
                .body(allocation);
        return restTemplate.exchange(request, VMDTO.class);
    }

    @PutMapping("addNetwork")
    public ResponseEntity<VMDTO> addNetwork(@RequestBody VMNetworkDTO allocation){
        RequestEntity<VMNetworkDTO> request = RequestEntity.put(baseUrl+"/vms/addNetwork")
                .contentType(MediaType.APPLICATION_JSON)
                .body(allocation);
        return restTemplate.exchange(request, VMDTO.class);
    }
}
