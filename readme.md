##TODO:

�� ������:

1) ������� ��� ����� ������ ������ ��� ����
�����, ��� ����� ���������� � GContext

MatrixBuffer{
	ModelMatrix
	ViewProjectionMatrix
}
ControlBuffer{
	float Alpha
}

2) ���������� ���������� UI � ECS
3) ������ ������� �� �������� �������� ������ (Canvas2D)
4) ������� ���� � ConstantBuffer

## 2

���������� GraphicsContext � 
struct Graphics{
	Device*device;
	Context*context;
}

Device �������� �� ��������� ��������
Context �������� �� ������������ ��������, ������ �������� � ������