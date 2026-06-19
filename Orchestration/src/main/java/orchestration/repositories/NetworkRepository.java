package orchestration.repositories;

import orchestration.models.Network;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface NetworkRepository extends JpaRepository<Network, Integer> {
    List<Network> findByOwner(Integer owner_id);
}
