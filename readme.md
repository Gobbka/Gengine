##TODO:

�� ������:

1) ���������� �� ��� ECS
2) ������ �������� RenderTarget � MaskEngine (�� DirectionLight)
3) 
4) ������� ����� ��������� render que, �� ������� 

State{matrix4x4;VertexShader;PixelShader}; 
RenderPipe->set_state(State);
RenderPipe->get_state();

5) ������� ��������� pipeline:
Technique:
|- vector<Step>

Step:
|- vector<Bindable>

Step::pass(){
	for(bindable in bindables){
		bindable.bind();
	}
}

�.� ������ �� ����������� ��� ������ IProbe*
template <T>
struct IProbe{
	std::vector<T> _array;

	void submit(T t){ _array.push_back(t);}
}

����������� Passer � ������� ����� ����� ����� �������/��������� ����� render pipeline
�.� ����� ��� ����� ������������ �� ���������:
1) ������� � ���������� �����
2) ������������ � ���������� �������� ����� ( �� �������� � �.�)
3) ��������������� ��� ������ � ���� �������
4) ������������� �������� �����
