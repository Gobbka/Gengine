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

Technique::pass(){
	for(step in steps){
		step.pass();
		drawModel();
	}
}
