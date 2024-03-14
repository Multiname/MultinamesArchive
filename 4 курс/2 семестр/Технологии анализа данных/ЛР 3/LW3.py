import pandas as pd
from statsmodels.tsa.arima.model import ARIMA
import matplotlib.pyplot as plt

# Считываем данные из файла Superstore.xls в структуру Dataframe
data = pd.read_excel("Superstore.xls")

# Выбираем данные, относящиеся ко всем подкатегориям
sub_categories_data = data.groupby('Sub-Category')

# Проходимся по каждой подкатегории
for sub_category, sub_category_df in sub_categories_data:
    # Группируем данные по годам и суммируем продажи
    yearly_sales = sub_category_df.groupby(pd.Grouper(key='Order Date', freq='Y'))['Sales'].sum()
    # Построение модели ARIMA
    model = ARIMA(yearly_sales, order=(5,1,0))
    model_fit = model.fit()
    # Прогноз на 5 лет вперёд
    forecast = model_fit.forecast(steps=5)
    # Вывод результатов прогноза
    print("Sub-Category:", sub_category)
    print("Forecast for next 5 years:")
    print(forecast)

    # Визуализация исходных данных и прогноза
    plt.figure(figsize=(10,6))
    plt.plot(yearly_sales.index, yearly_sales, label='Actual Sales')
    plt.plot(pd.date_range(start=yearly_sales.index[-1], periods=6, freq='Y')[1:], forecast, label='Forecast')
    plt.title("ARIMA Forecast for {}".format(sub_category))
    plt.xlabel("Year")
    plt.ylabel("Sales")
    plt.legend()
    plt.show()

    # Оценка качества модели
    residuals = model_fit.resid
    variance = residuals.var()
    std_deviation = residuals.std()
    print("Variance:", variance)
    print("Standard Deviation:", std_deviation)
