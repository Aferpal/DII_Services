package orchestration.exceptions;

public class InvalidVMException extends RuntimeException {
    public InvalidVMException(String message) {
        super(message);
    }
}
