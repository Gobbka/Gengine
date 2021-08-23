##TODO:

Ќа завтра:

1) вынести отрисовку канваса в отдельный RenderPass
2) вынести 2DLayer в ECS
3) ƒобавить нормали и PointLight

## 2

переделать GraphicsContext в 
struct Graphics{
	Device*device;
	Context*context;
}

Device отвечает за аллокацию ресурсов
Context отвечает за установление шейдеров, шейдер ресурсов и прочее