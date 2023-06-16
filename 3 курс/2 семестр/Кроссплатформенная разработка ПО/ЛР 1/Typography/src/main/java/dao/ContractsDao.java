package dao;

import models.Contract;
import org.hibernate.Session;
import org.hibernate.Transaction;
import utils.HibernateSessionFactoryUtil;

import java.util.List;

public class ContractsDao {
    public Contract FindById(long id) {
        Session session = HibernateSessionFactoryUtil.getSessionFactory().openSession();
        Contract contract = session.get(Contract.class, id);
        session.close();
        return contract;
    }

    public List<Contract> FindAll() {
        Session session = HibernateSessionFactoryUtil.getSessionFactory().openSession();
        List<Contract> contracts = (List<Contract>) session.createQuery("From Contract").list();
        session.close();
        return contracts;
    }

    public void Save(Contract contract) {
        Session session = HibernateSessionFactoryUtil.getSessionFactory().openSession();
        Transaction tx = session.beginTransaction();
        session.save(contract);
        tx.commit();
        session.close();
    }

    public void Update(Contract contract) {
        Session session = HibernateSessionFactoryUtil.getSessionFactory().openSession();
        Transaction tx = session.beginTransaction();
        session.update(contract);
        tx.commit();
        session.close();
    }

    public void Delete(Contract contract) {
        Session session = HibernateSessionFactoryUtil.getSessionFactory().openSession();
        Transaction tx = session.beginTransaction();
        session.delete(contract);
        tx.commit();
        session.close();
    }
}
