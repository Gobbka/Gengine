##TODO:

Ќа завтра:

2) ѕродолжить переносить UI в ECS
3) ”брать костыль не удалени€ вертекса вершин (Canvas2D)
4) ¬ынести свет в ConstantBuffer

## 2

переделать GraphicsContext в 
struct Graphics{
	Device*device;
	Context*context;
}

Device отвечает за аллокацию ресурсов
Context отвечает за установление шейдеров, шейдер ресурсов и прочее