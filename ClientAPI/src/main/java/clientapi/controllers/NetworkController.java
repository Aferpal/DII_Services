package clientapi.controllers;

import clientapi.DTOs.NetworkDTO;
import clientapi.DTOs.NetworkNewDTO;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.http.MediaType;
import org.springframework.http.RequestEntity;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.client.RestTemplate;

import java.util.List;

@RestController
@RequestMapping("/networks")
public class NetworkController {
    RestTemplate restTemplate;

    @Value("${externalServerUrl}")
    private String baseUrl;

    @Autowired
    public NetworkController(RestTemplate restTemplate){
        this.restTemplate = restTemplate;
    }

    @GetMapping("")
    public ResponseEntity<NetworkDTO[]> getAllUserNetworks(@RequestParam(name = "user") Integer user_id){
        return restTemplate.getForEntity(baseUrl+"/networks?user="+user_id, NetworkDTO[].class);
    }

    @PostMapping("")
    public ResponseEntity<NetworkDTO> createNetwork(@RequestBody NetworkNewDTO body){
        RequestEntity<NetworkNewDTO> request = RequestEntity.post(baseUrl+"/networks")
                .contentType(MediaType.APPLICATION_JSON)
                .body(body);
        return restTemplate.exchange(request, NetworkDTO.class);
    }
}
