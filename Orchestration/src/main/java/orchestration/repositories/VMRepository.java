package orchestration.repositories;

import orchestration.models.VM;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface VMRepository extends JpaRepository<VM, Long> {
}
