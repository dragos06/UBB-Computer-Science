import controller.Controller;
import repository.IRepository;
import controller.IController;
import repository.Repository;
import view.IView;
import view.View;

public class Main {
    public static void main(String[] args) {
        IRepository repository = new Repository();
        IController controller = new Controller(repository);
        IView view = new View(controller);

        view.run();
    }
}
