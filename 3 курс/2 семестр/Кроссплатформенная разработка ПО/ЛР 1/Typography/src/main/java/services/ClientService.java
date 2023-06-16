package services;

import dao.ClientsDao;
import models.Client;
import java.util.List;

public class ClientService {
    private ClientsDao clientsDao = new ClientsDao();

    public ClientService() {}

    public Client FindClient(long id) { return clientsDao.FindById(id); }
    public List<Client> FindAllClients() { return clientsDao.FindAll(); }
    public void SaveClient(Client client) { clientsDao.Save(client); }
    public void DeleteClient(Client client) { clientsDao.Delete(client); }
    public void UpdateClient(Client client) { clientsDao.Update(client); }
}
