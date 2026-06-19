package orchestration.exceptions;

public class MismatchingOwnerException extends RuntimeException {
    public MismatchingOwnerException(String message) {
        super(message);
    }
}
