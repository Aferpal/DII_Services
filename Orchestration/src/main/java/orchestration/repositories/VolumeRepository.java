package orchestration.repositories;

import orchestration.models.Volume;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface VolumeRepository extends JpaRepository<Volume, Integer> {
    List<Volume> findByOwner(Integer owner_id);
}
