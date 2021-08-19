##TODO:

На завтра:

1) переписать всё под ECS
2) решить конфликт RenderTarget и MaskEngine (см DirectionLight)
3) 
4) Сделать класс состояния render que, на подобии 

State{matrix4x4;VertexShader;PixelShader}; 
RenderPipe->set_state(State);
RenderPipe->get_state();

5) Сделать следующий pipeline:
Technique:
|- vector<Step>

Step:
|- vector<Bindable>

Step::pass(){
	for(bindable in bindables){
		bindable.bind();
	}
}

т.е сперва мы прощупываем все модели IProbe*
template <T>
struct IProbe{
	std::vector<T> _array;

	void submit(T t){ _array.push_back(t);}
}

Реализовать Passer в котором можно будет гибко удалять/добавлять этапы render pipeline
т.е можно все этапы распределить на категории:
1) Очистка и подготовка сцены
2) Исследование и фильтрация обьектов сцены ( по техникам и т.д)
3) Непосредственно сам рендер и пост эффекты
4) Представление готового кадра
