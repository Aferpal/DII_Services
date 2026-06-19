package orchestration.exceptions;

import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.RestControllerAdvice;

@RestControllerAdvice
public class ServiceExceptionHandler {

    @ExceptionHandler({InvalidVMException.class,
                        InvalidNetworkException.class,
                        InvalidVolumeException.class
    })
    public ResponseEntity<Void> handleInvalidEntity(RuntimeException ex){
        System.out.println("[ EXCEPTION ] Se ha recibido una excepción con el mensaje:\n" + ex.getMessage());
        return ResponseEntity.notFound().build();
    }

    @ExceptionHandler({MismatchingOwnerException.class})
    public ResponseEntity<Void> handleMismatchedOwner(RuntimeException ex){
        System.out.println("[ EXCEPTION ] Se ha recibido una excepción con el mensaje:\n" + ex.getMessage());
        return ResponseEntity.status(HttpStatus.FORBIDDEN).build();
    }
}
