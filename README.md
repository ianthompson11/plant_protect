# plant_protect
El proyecto muestra el desarrollo y evolucion de un sistema de automatizacion de cultivos, desde la deteccion individual de estos hasta sus cuidados especificos


Antes de que el proyecto pueda ser funcional para el equipo de desarrollo es necesario algunas modificaciones:

1. Modificar los archivos de jupyter notebook con todo lo necesario para las instalaciones evitando posibles errores.
2. Añadir al codigo una seccion que permita que el modelo ya entrenado, el cual se encuentra en archivo de tipo .zip pueda ser guardado en la carpeta necesaria para su funcionamiento
3. Exportar la base de datos para ser utilizada en otros equipos, es preferible colocar instrucciones para que el resto del equipo pueda incluir la base de datos en su equipo y los archivos de la bade de datos deben subirse a este proyecto tambien.
4. Realizar adecuaciones para el funcionamiento apropiado del codigo en todo tipo de tamaños de pantalla, actualmente los tamaños de ciertas imagenes son gestionados especificamente para dos tamaños distintos de pantalla, es necesario que se adecuen para que el mismo codigo independientemente del tamaño de pantalla muestre adecuadamente las imagenes.



## COPIA DE SEGURIDAD DE LA BASE DE DATOS:

Como por ahora se estara trabajando con una base de datos que se va a encontrar de manera local en cada ordenador, es necesario usar el archivo de copia de seguridad y adicionarlo manualmente a sql server management studio, en este caso el archivo necesario es 'Plant_protect.bak'
1. Dirijase a la carpeta del proyecto en donde deberia estar el archivo antes mencionado
2. Copie el archivo y peguelo en la siguiente ruta: "C:\Program Files\Microsoft SQL Server\MSSQL16.SQLEXPRESS\MSSQL\Backup"
3. Abra SQL Server Management Studio
![image](https://github.com/user-attachments/assets/bbab20cd-cf01-4f77-90b5-c358f92e91c1)
4. De un click derecho en Databases y seleccione la opcion para restaurar
   ![image](https://github.com/user-attachments/assets/f519d71c-8e8f-47ea-8f3b-066cd12a7dc5)
5. Le aparecera una ventana como la que se muestra en la imagen, aqui debe seleccionar devices o dispositivos
   ![image](https://github.com/user-attachments/assets/e8fd0bc9-5ab0-4c75-b159-424d48d4b321)
6. Seleccione los tres puntitos que se encuentran alado de devices
7. Se le abrira una ventana similar a la de la imagen, alli debe seleccionar add o agregar
   ![image](https://github.com/user-attachments/assets/32e6cea3-e682-4a93-94ab-1bc3639692c5)
8. Dirijase a la ruta en la que puso su base de datos, recuerde que es la ruta del punto 2 y seleccione el archivo .bak
   ![image](https://github.com/user-attachments/assets/79fb5128-ca69-4330-b475-f70277ce72a9)
9. Luego presione OK en las ventanas anteriores hasta que la base de datos aparezca en SQL Server Management Studio







