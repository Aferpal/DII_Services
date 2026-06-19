package orchestration.repositories;

import orchestration.models.VM;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface VMRepository extends JpaRepository<VM, Integer> {
    List<VM> findByOwner(Integer owner_id);
}
