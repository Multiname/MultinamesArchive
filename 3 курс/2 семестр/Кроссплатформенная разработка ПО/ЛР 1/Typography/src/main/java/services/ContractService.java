package services;

import dao.ContractsDao;
import models.Contract;
import java.util.List;

public class ContractService {
    private ContractsDao contractsDao = new ContractsDao();

    public ContractService() {}

    public Contract FindContract(long id) { return contractsDao.FindById(id); }
    public List<Contract> FindAllContracts() { return contractsDao.FindAll(); }
    public void SaveContract(Contract contract) { contractsDao.Save(contract); }
    public void DeleteContract(Contract contract) { contractsDao.Delete(contract); }
    public void UpdateContract(Contract contract) { contractsDao.Update(contract); }
}
