import repository.Repository;
import repository.IRepository;
import controller.Controller;
import view.View;

public class Main {
    public static void main(String[] args) {
        IRepository repository = new Repository();
        Controller controller = new Controller(repository);
        View view = new View(controller);

        view.run();
    }
}