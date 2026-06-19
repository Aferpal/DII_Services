package orchestration.repositories;

import orchestration.models.VMNetwork;
import orchestration.models.VMNetworkID;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface VMNetworkRepository extends JpaRepository<VMNetwork, VMNetworkID> {

}
