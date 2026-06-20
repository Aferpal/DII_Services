package clientapi.controllers;

import clientapi.DTOs.VolumeDTO;
import clientapi.DTOs.VolumeNewDTO;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.http.MediaType;
import org.springframework.http.RequestEntity;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.client.RestTemplate;

import java.util.List;

@RestController
@RequestMapping("/volumes")
public class VolumeController {
    RestTemplate restTemplate;

    @Value("${externalServerUrl}")
    private String baseUrl;

    @Autowired
    public VolumeController(RestTemplate restTemplate){
        this.restTemplate = restTemplate;
    }

    @GetMapping("")
    public ResponseEntity<VolumeDTO[]> getAllUserVolumes(@RequestParam(name = "user") Integer user_id){
        return restTemplate.getForEntity(baseUrl+"/volumes?user="+user_id, VolumeDTO[].class);
    }

    @PostMapping("")
    public ResponseEntity<VolumeDTO> createExamen(@RequestBody VolumeNewDTO body){
        RequestEntity<VolumeNewDTO> request = RequestEntity.post(baseUrl+"/volumes")
                .contentType(MediaType.APPLICATION_JSON)
                .body(body);
        return restTemplate.exchange(request, VolumeDTO.class);
    }
}
