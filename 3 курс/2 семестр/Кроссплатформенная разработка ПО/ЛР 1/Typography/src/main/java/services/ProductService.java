package services;

import dao.ProductsDao;
import models.Product;
import java.util.List;

public class ProductService {
    private ProductsDao productsDao = new ProductsDao();

    public ProductService() {}

    public Product FindProduct(long id) { return productsDao.FindById(id); }
    public List<Product> FindAllProducts() { return productsDao.FindAll(); }
    public void SaveProduct(Product product) { productsDao.Save(product); }
    public void DeleteProduct(Product product) { productsDao.Delete(product); }
    public void UpdateProduct(Product product) { productsDao.Update(product); }
}