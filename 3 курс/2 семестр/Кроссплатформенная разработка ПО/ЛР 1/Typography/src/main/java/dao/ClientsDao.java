package dao;

import models.Client;
import org.hibernate.Session;
import org.hibernate.Transaction;
import utils.HibernateSessionFactoryUtil;
import java.util.List;

public class ClientsDao {
    public Client FindById(long id) {
        Session session = HibernateSessionFactoryUtil.getSessionFactory().openSession();
        Client client = session.get(Client.class, id);
        session.close();
        return client;
    }

    public List<Client> FindAll() {
        Session session = HibernateSessionFactoryUtil.getSessionFactory().openSession();
        List<Client> clients = (List<Client>) session.createQuery("From Client").list();
        session.close();
        return clients;
    }

    public void Save(Client client) {
        Session session = HibernateSessionFactoryUtil.getSessionFactory().openSession();
        Transaction tx = session.beginTransaction();
        session.save(client);
        tx.commit();
        session.close();
    }

    public void Update(Client client) {
        Session session = HibernateSessionFactoryUtil.getSessionFactory().openSession();
        Transaction tx = session.beginTransaction();
        session.update(client);
        tx.commit();
        session.close();
    }

    public void Delete(Client client) {
        Session session = HibernateSessionFactoryUtil.getSessionFactory().openSession();
        Transaction tx = session.beginTransaction();
        session.delete(client);
        tx.commit();
        session.close();
    }
}
