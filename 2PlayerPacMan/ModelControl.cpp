#if 0
#include "ModelControl.h"

const int FRAMEDELAY = 10;
const int GAMEDELAY = 2;

ModelControl::ModelControl(Game& view) : _view(view), _state(START), _running(false), _lives(3), _sprites(5, nullptr), _p1move(false), _p2move(false)
{
	_f = Pacman("Female");
	_m = Pacman("Male");
	_b = Ghost("DinoB");;
	_g = Ghost("DinoG");
	_r = Ghost("DinoR");
	_y = Ghost("DinoY");

	Init();
	StartInit();
}

ModelControl::~ModelControl()
{
	al_destroy_sample(_music);
	al_destroy_sample(_chase);
	al_destroy_sample(_countdown);
	al_destroy_sample(_death);
	al_destroy_sample(_end);
	al_destroy_sample(_thump);
}

void ModelControl::Click()
{
	int ind = -1;
	if (_state == P1PICK)
		ind = 0;
	if (_state == P2PICK)
		ind = 1;
	if (ind == -1)
		return;
	
	int cx = -1;
	int cy = -1;
	_view.CursorPosition(cx, cy);

	if (ind == 0 && 115 <= cx && cx <= 435 && 245 <= cy && cy <= 565)
	{
		_sprites[ind] = &_f;
		_state = (State)((int)_state + 1);
	}
	else if (ind == 0 && 835 <= cx && cx <= 1155 && 245 <= cy && cy <= 565)
	{
		_sprites[ind] = &_m;
		_state = (State)((int)_state + 1);
	}

	if (ind == 1 && 75 <= cx && cx <= 315 && 285 <= cy && cy <= 525)
	{
		_sprites[ind] = &_b;
		_sprites[2] = &_g;
		_sprites[3] = &_r;
		_sprites[4] = &_y;
		_state = (State)((int)_state + 1);
	}
	else if (ind == 1 && 335 <= cx && cx <= 575 && 285 <= cy && cy <= 525)
	{
		_sprites[ind] = &_g;
		_sprites[2] = &_b;
		_sprites[3] = &_r;
		_sprites[4] = &_y;
		_state = (State)((int)_state + 1);
	}
	else if (ind == 1 && 635 <= cx && cx <= 875 && 285 <= cy && cy <= 525)
	{
		_sprites[ind] = &_r;
		_sprites[2] = &_b;
		_sprites[3] = &_g;
		_sprites[4] = &_y;
		_state = (State)((int)_state + 1);
	}
	else if (ind == 1 && 915 <= cx && cx <= 1155 && 285 <= cy && cy <= 525)
	{
		_sprites[ind] = &_y;
		_sprites[2] = &_b;
		_sprites[3] = &_g;
		_sprites[4] = &_r;
		_state = (State)((int)_state + 1);
	}

	Initialization();
}

void ModelControl::Next()
{
	if (_state == P1PICK || _state == P2PICK)
		return;

	if (!_running)
	{
		if (_state == GAME)
		{
			_lives -= 1;
			if (_lives == 0)
			{
				_state = (State)((int)_state + 1);
				Initialization();
			}
		}
		else
		{
			_state = (State)((int)_state + 1);
			Initialization();
		}

	}
}

void ModelControl::Move(int player, EventType move)
{
	if (_state != GAME)
		return;

	if (player == 0)
		_p1move = true;
	if (player == 1)
		_p2move = true;

	switch (move)
	{
		case EV_UP:
			_sprites[player]->SetY(_sprites[player]->GetY() - _sprites[player]->GetSpeed());
			return;
		case EV_DOWN:
			_sprites[player]->SetY(_sprites[player]->GetY() + _sprites[player]->GetSpeed());
			return;
		case EV_LEFT:
			_sprites[player]->SetX(_sprites[player]->GetX() - _sprites[player]->GetSpeed());
			_sprites[player]->SetDir(false);
			return;
		case EV_RIGHT:
			_sprites[player]->SetX(_sprites[player]->GetX() + _sprites[player]->GetSpeed());
			_sprites[player]->SetDir(true);
			return;
	}

	_sprites[player]->SetState(1);
}

void ModelControl::Draw()
{
	switch (_state)
	{
		case START:
			Start();
			break;
		case P1PICK:
			P1Pick();
			break;
		case P2PICK:
			P2Pick();
			break;
		case GAME:
			Maze();
			break;
		case END:
			End();
			break;
		case OVER:
			_view.Done();
			break;
	}
}

void ModelControl::Start()
{
	std::vector<ALLEGRO_BITMAP*> fImage = _f.GetAnnimation(2);
	std::vector<ALLEGRO_BITMAP*> mImage = _m.GetAnnimation(2);
	std::vector<ALLEGRO_BITMAP*> bImage = _b.GetAnnimation(2);
	std::vector<ALLEGRO_BITMAP*> gImage = _g.GetAnnimation(2);
	std::vector<ALLEGRO_BITMAP*> rImage = _r.GetAnnimation(2);
	std::vector<ALLEGRO_BITMAP*> yImage = _y.GetAnnimation(2);

	_view.DrawImageScaled(_background, 0, 0, _view.GetW(), _view.GetH());
	_view.DrawImage(_textTitle, 277, 150);
	_view.DrawImageScaled(_textEnter, 403, 250, 463, 19);

	_f.SetFrameCount(_f.GetFrameCount() + 1);
	if (_f.GetFrameCount() >= FRAMEDELAY)
	{
		_f.SetCurFrame(_f.GetCurFrame() + 1);
		if (_f.GetCurFrame() >= fImage.size())
			_f.SetCurFrame(0);
		_f.SetFrameCount(0);
	}
	_m.SetFrameCount(_m.GetFrameCount() + 1);
	if (_m.GetFrameCount() >= FRAMEDELAY)
	{
		_m.SetCurFrame(_m.GetCurFrame() + 1);
		if (_m.GetCurFrame() >= fImage.size())
			_m.SetCurFrame(0);
		_m.SetFrameCount(0);
	}
	_b.SetFrameCount(_b.GetFrameCount() + 1);
	if (_b.GetFrameCount() >= FRAMEDELAY)
	{
		_b.SetCurFrame(_b.GetCurFrame() + 1);
		if (_b.GetCurFrame() >= fImage.size())
			_b.SetCurFrame(0);
		_b.SetFrameCount(0);
	}
	_g.SetFrameCount(_g.GetFrameCount() + 1);
	if (_g.GetFrameCount() >= FRAMEDELAY)
	{
		_g.SetCurFrame(_g.GetCurFrame() + 1);
		if (_g.GetCurFrame() >= fImage.size())
			_g.SetCurFrame(0);
		_g.SetFrameCount(0);
	}
	_r.SetFrameCount(_r.GetFrameCount() + 1);
	if (_r.GetFrameCount() >= FRAMEDELAY)
	{
		_r.SetCurFrame(_r.GetCurFrame() + 1);
		if (_r.GetCurFrame() >= fImage.size())
			_r.SetCurFrame(0);
		_r.SetFrameCount(0);
	}
	_y.SetFrameCount(_y.GetFrameCount() + 1);
	if (_y.GetFrameCount() >= FRAMEDELAY)
	{
		_y.SetCurFrame(_y.GetCurFrame() + 1);
		if (_y.GetCurFrame() >= fImage.size())
			_y.SetCurFrame(0);
		_y.SetFrameCount(0);
	}

	_view.DrawImageScaled(fImage[_f.GetCurFrame()], _f.GetX(), _f.GetY(), 84, 84);
	_view.DrawImageScaled(mImage[_m.GetCurFrame()], _m.GetX(), _m.GetY(), 84, 84);
	_view.DrawImageScaled(bImage[_b.GetCurFrame()], _b.GetX(), _b.GetY(), 84, 84);
	_view.DrawImageScaled(gImage[_g.GetCurFrame()], _g.GetX(), _g.GetY(), 84, 84);
	_view.DrawImageScaled(rImage[_r.GetCurFrame()], _r.GetX(), _r.GetY(), 84, 84);
	_view.DrawImageScaled(yImage[_y.GetCurFrame()], _y.GetX(), _y.GetY(), 84, 84);

	int speed = 4;
	_f.SetX(_f.GetX() + speed);
	_m.SetX(_m.GetX() + speed);
	_b.SetX(_b.GetX() + speed);
	_g.SetX(_g.GetX() + speed);
	_r.SetX(_r.GetX() + speed);
	_y.SetX(_y.GetX() + speed);

	if (_f.GetX() > _view.GetW())
		_f.SetX(-84);
	if (_m.GetX() > _view.GetW())
		_m.SetX(-84);
	if (_b.GetX() > _view.GetW())
		_b.SetX(-84);
	if (_g.GetX() > _view.GetW())
		_g.SetX(-84);
	if (_r.GetX() > _view.GetW())
		_r.SetX(-84);
	if (_y.GetX() > _view.GetW())
		_y.SetX(-84);
}

void ModelControl::P1Pick()
{
	vector<ALLEGRO_BITMAP*> fImage = _f.GetAnnimation(3);
	vector<ALLEGRO_BITMAP*> mImage = _m.GetAnnimation(3);

	_view.DrawImageScaled(_background, 0, 0, _view.GetW(), _view.GetH());
	_view.DrawImageScaled(_textP1, 204, 50, 862, 38);
	_view.DrawImage(_box, 115, 245);
	_view.DrawImage(_box, 835, 245);

	_f.SetFrameCount(_f.GetFrameCount() + 1);
	if (_f.GetFrameCount() >= FRAMEDELAY)
	{
		_f.SetCurFrame(_f.GetCurFrame() + 1);
		if (_f.GetCurFrame() >= fImage.size())
			_f.SetCurFrame(0);
		_f.SetFrameCount(0);
	}
	_m.SetFrameCount(_m.GetFrameCount() + 1);
	if (_m.GetFrameCount() >= FRAMEDELAY)
	{
		_m.SetCurFrame(_m.GetCurFrame() + 1);
		if (_m.GetCurFrame() >= fImage.size())
			_m.SetCurFrame(0);
		_m.SetFrameCount(0);
	}

	_view.DrawImageScaled(fImage[_f.GetCurFrame()], _f.GetX(), _f.GetY(), 252, 252);
	_view.DrawImageScaled(mImage[_m.GetCurFrame()], _m.GetX(), _m.GetY(), 252, 252);
}

void ModelControl::P2Pick()
{
	std::vector<ALLEGRO_BITMAP*> bImage = _b.GetAnnimation(3);
	std::vector<ALLEGRO_BITMAP*> gImage = _g.GetAnnimation(3);
	std::vector<ALLEGRO_BITMAP*> rImage = _r.GetAnnimation(3);
	std::vector<ALLEGRO_BITMAP*> yImage = _y.GetAnnimation(3);

	_view.DrawImageScaled(_background, 0, 0, _view.GetW(), _view.GetH());
	_view.DrawImageScaled(_textP2, 194, 50, 883, 38);
	_view.DrawImageScaled(_box, 75, 285, 240, 240);
	_view.DrawImageScaled(_box, 355, 285, 240, 240);
	_view.DrawImageScaled(_box, 635, 285, 240, 240);
	_view.DrawImageScaled(_box, 915, 285, 240, 240);

	_b.SetFrameCount(_b.GetFrameCount() + 1);
	if (_b.GetFrameCount() >= FRAMEDELAY)
	{
		_b.SetCurFrame(_b.GetCurFrame() + 1);
		if (_b.GetCurFrame() >= bImage.size())
			_b.SetCurFrame(0);
		_b.SetFrameCount(0);
	}
	_g.SetFrameCount(_g.GetFrameCount() + 1);
	if (_g.GetFrameCount() >= FRAMEDELAY)
	{
		_g.SetCurFrame(_g.GetCurFrame() + 1);
		if (_g.GetCurFrame() >= gImage.size())
			_g.SetCurFrame(0);
		_g.SetFrameCount(0);
	}
	_r.SetFrameCount(_r.GetFrameCount() + 1);
	if (_r.GetFrameCount() >= FRAMEDELAY)
	{
		_r.SetCurFrame(_r.GetCurFrame() + 1);
		if (_r.GetCurFrame() >= rImage.size())
			_r.SetCurFrame(0);
		_r.SetFrameCount(0);
	}
	_y.SetFrameCount(_y.GetFrameCount() + 1);
	if (_y.GetFrameCount() >= FRAMEDELAY)
	{
		_y.SetCurFrame(_y.GetCurFrame() + 1);
		if (_y.GetCurFrame() >= yImage.size())
			_y.SetCurFrame(0);
		_y.SetFrameCount(0);
	}

	_view.DrawImageScaled(bImage[_b.GetCurFrame()], _b.GetX(), _b.GetY(), 189, 189);
	_view.DrawImageScaled(gImage[_g.GetCurFrame()], _g.GetX(), _g.GetY(), 189, 189);
	_view.DrawImageScaled(rImage[_r.GetCurFrame()], _r.GetX(), _r.GetY(), 189, 189);
	_view.DrawImageScaled(yImage[_y.GetCurFrame()], _y.GetX(), _y.GetY(), 189, 189);
}

void ModelControl::Maze()
{
	if (!_running)
		return;

	ALLEGRO_BITMAP* ltext = al_load_bitmap("Assets/Game/life.png");
	ALLEGRO_BITMAP* life = _sprites[0]->GetAnnimation(_sprites[0]->GetState())[0];
	int lifex = 10;
	int lifey = 765;

	vector<ALLEGRO_BITMAP*> p1Image = _sprites[0]->GetAnnimation(_sprites[0]->GetState());
	vector<ALLEGRO_BITMAP*> p2Image = _sprites[1]->GetAnnimation(_sprites[1]->GetState());
	vector<ALLEGRO_BITMAP*> g1Image = _sprites[2]->GetAnnimation(_sprites[2]->GetState());
	vector<ALLEGRO_BITMAP*> g2Image = _sprites[3]->GetAnnimation(_sprites[3]->GetState());
	vector<ALLEGRO_BITMAP*> g3Image = _sprites[4]->GetAnnimation(_sprites[4]->GetState());

	_view.DrawImageScaled(_maze, 0, 0, _view.GetW(), _view.GetH());

	if (_p1move)
	{
		p1Image = _sprites[0]->GetAnnimation(_sprites[0]->GetState());
		_sprites[0]->SetFrameCount(FRAMEDELAY);
		_sprites[0]->SetCurFrame(p1Image.size());
		//WallCollision(_sprites[0]);
		_p1move = false;
		_sprites[0]->SetState(3);
	}
	if (_p2move)
	{
		p2Image = _sprites[1]->GetAnnimation(_sprites[1]->GetState());
		_sprites[1]->SetFrameCount(FRAMEDELAY);
		_sprites[1]->SetCurFrame(p2Image.size());
		//WallCollision(_sprites[1]);
		_p2move = false;
		_sprites[1]->SetState(3);
	}

	_sprites[0]->SetFrameCount(_sprites[0]->GetFrameCount() + 1);
	if (_sprites[0]->GetFrameCount() >= FRAMEDELAY)
	{
		_sprites[0]->SetCurFrame(_sprites[0]->GetCurFrame() + 1);
		if (_sprites[0]->GetCurFrame() >= p1Image.size())
			_sprites[0]->SetCurFrame(0);
		_sprites[0]->SetFrameCount(0);
	}
	_sprites[1]->SetFrameCount(_sprites[1]->GetFrameCount() + 1);
	if (_sprites[1]->GetFrameCount() >= FRAMEDELAY)
	{
		_sprites[1]->SetCurFrame(_sprites[1]->GetCurFrame() + 1);
		if (_sprites[1]->GetCurFrame() >= p2Image.size())
			_sprites[1]->SetCurFrame(0);
		_sprites[1]->SetFrameCount(0);
	}

	_view.DrawImageScaled(p1Image[_sprites[0]->GetCurFrame()], _sprites[0]->GetX(), _sprites[0]->GetY(), 36, 36);
	_view.DrawImageScaled(p2Image[_sprites[1]->GetCurFrame()], _sprites[1]->GetX(), _sprites[1]->GetY(), 36, 36);

	_sprites[2]->SetFrameCount(_sprites[2]->GetFrameCount() + 1);
	if (_sprites[2]->GetFrameCount() >= FRAMEDELAY)
	{
		_sprites[2]->SetCurFrame(_sprites[2]->GetCurFrame() + 1);
		if (_sprites[2]->GetCurFrame() >= g1Image.size())
			_sprites[2]->SetCurFrame(0);
		_sprites[2]->SetFrameCount(0);
	}
	_sprites[3]->SetFrameCount(_sprites[3]->GetFrameCount() + 1);
	if (_sprites[3]->GetFrameCount() >= FRAMEDELAY)
	{
		_sprites[3]->SetCurFrame(_sprites[3]->GetCurFrame() + 1);
		if (_sprites[3]->GetCurFrame() >= g2Image.size())
			_sprites[3]->SetCurFrame(0);
		_sprites[3]->SetFrameCount(0);
	}
	_sprites[4]->SetFrameCount(_sprites[4]->GetFrameCount() + 1);
	if (_sprites[4]->GetFrameCount() >= FRAMEDELAY)
	{
		_sprites[4]->SetCurFrame(_sprites[4]->GetCurFrame() + 1);
		if (_sprites[4]->GetCurFrame() >= g3Image.size())
			_sprites[4]->SetCurFrame(0);
		_sprites[4]->SetFrameCount(0);
	}

	//WallCollision(_sprites[2]);
	//WallCollision(_sprites[3]);
	//WallCollision(_sprites[4]);

	_view.DrawImageScaled(g1Image[_sprites[2]->GetCurFrame()], _sprites[2]->GetX(), _sprites[2]->GetY(), 36, 36);
	_view.DrawImageScaled(g2Image[_sprites[3]->GetCurFrame()], _sprites[3]->GetX(), _sprites[3]->GetY(), 36, 36);
	_view.DrawImageScaled(g3Image[_sprites[4]->GetCurFrame()], _sprites[4]->GetX(), _sprites[4]->GetY(), 36, 36);

	_view.DrawImageScaled(ltext, lifex + 10, lifey - 10, 50, 13);
	for (int i = 0; i < _lives; i++)
	{
		_view.DrawImageScaled(life, lifex + i * 40, lifey, 36, 36);
	}

	if (GhostCollision(_sprites[1]) || GhostCollision(_sprites[2]) || GhostCollision(_sprites[3]) || GhostCollision(_sprites[4]))
	{
		_running = false;
	}
}

void ModelControl::End()
{
	
}

void ModelControl::Countdown()
{
	_view.AudioPlay(_countdown);

	_view.DrawImageScaled(_maze, 0, 0, _view.GetW(), _view.GetH());
	_view.DrawImage(_c3, 600, 400);
	al_flip_display();
	al_rest(1);
	_view.DrawImageScaled(_maze, 0, 0, _view.GetW(), _view.GetH());
	_view.DrawImage(_c2, 600, 400);
	al_flip_display();
	al_rest(1);
	_view.DrawImageScaled(_maze, 0, 0, _view.GetW(), _view.GetH());
	_view.DrawImage(_c1, 600, 400);
	al_flip_display();
	al_rest(1);
	_view.DrawImageScaled(_maze, 0, 0, _view.GetW(), _view.GetH());
	_view.DrawImage(_cs, 450, 400);
	al_flip_display();
	al_rest(1);

	_view.AudioStop();
}

bool ModelControl::GhostCollision(Player* ghost)
{
	int ptlx = _sprites[0]->GetX() + 6;
	int ptly = _sprites[0]->GetY() + 9;
	int pbrx = ptlx + 24;
	int pbry = ptly + 24;

	int gtlx = ghost->GetX() + 6;
	int gtly = ghost->GetY() + 9;
	int gbrx = gtlx + 24;
	int gbry = gtly + 24;

	if (ptlx > gbrx || gtlx > pbrx)
		return false;

	if (pbry < gtly || gbry < ptly)
		return false;

	return true;
}

bool ModelControl::WallCollision(Player* p)
{
	int tlx = p->GetX() + 6;
	int tly = p->GetY() + 9;
	int brx = tlx + 24;
	int bry = tly + 24;

	ALLEGRO_COLOR tl = al_get_pixel(_maze, tlx, tly);
	ALLEGRO_COLOR tr = al_get_pixel(_maze, brx, tly);
	ALLEGRO_COLOR bl = al_get_pixel(_maze, tlx, bry);
	ALLEGRO_COLOR br = al_get_pixel(_maze, brx, bry);

	float WALLR = 0.839216;

	if (fabs(tl.r - WALLR) < 0.01)
	{
		p->SetX(p->GetX() + p->GetSpeed());
		p->SetY(p->GetY() + p->GetSpeed());
		return true;
	}
	if (fabs(tr.r - WALLR) < 0.01)
	{
		p->SetX(p->GetX() - p->GetSpeed());
		p->SetY(p->GetY() + p->GetSpeed());
		return true;
	}
	if (fabs(bl.r - WALLR) < 0.01)
	{
		p->SetX(p->GetX() + p->GetSpeed());
		p->SetY(p->GetY() - p->GetSpeed());
		return true;
	}
	if (fabs(br.r - WALLR) < 0.01)
	{
		p->SetX(p->GetX() - p->GetSpeed());
		p->SetY(p->GetY() - p->GetSpeed());
		return true;
	}

	return false;
}

void ModelControl::Init()
{
	al_reserve_samples(6);
	_music = al_load_sample("Assets/Sounds/music.wav");
	_chase = al_load_sample("Assets/Sounds/chase.wav");
	_countdown = al_load_sample("Assets/Sounds/countdown.wav");
	_death = al_load_sample("Assets/Sounds/death.wav");
	_end = al_load_sample("Assets/Sounds/end.wav");
	_thump = al_load_sample("Assets/Sounds/thump.wav");
	if (!_music)
	{
		cout << "Failed to create music sample\n";
		exit(-1);
	}
	if (!_chase)
	{
		cout << "Failed to create chase sample\n";
		exit(-1);
	}
	if (!_countdown)
	{
		cout << "Failed to create countdown sample\n";
		exit(-1);
	}
	if (!_death)
	{
		cout << "Failed to create death sample\n";
		exit(-1);
	}
	if (!_end)
	{
		cout << "Failed to create end sample\n";
		exit(-1);
	}
	if (!_thump)
	{
		cout << "Failed to create thump sample\n";
		exit(-1);
	}

	_background = al_load_bitmap("Assets/background.jpg");
	_textTitle = al_load_bitmap("Assets/Start/title.png");
	_textEnter = al_load_bitmap("Assets/Start/enter.png");
	_textP1 = al_load_bitmap("Assets/Start/p1.png");
	_box = al_load_bitmap("Assets/Start/box.png");
	_textP2 = al_load_bitmap("Assets/Start/p2.png");
	_maze = al_load_bitmap("Assets/Game/maze.png");
	_c3 = al_load_bitmap("Assets/Game/3.png");
	_c2 = al_load_bitmap("Assets/Game/2.png");
	_c1 = al_load_bitmap("Assets/Game/1.png");
	_cs = al_load_bitmap("Assets/Game/start.png");
}

void ModelControl::Initialization()
{
	switch (_state)
	{
		case P1PICK:
			P1PickInit();
			return;
		case P2PICK:
			P2PickInit();
			return;
		case GAME:
			MazeInit();
			return;
	}
}

void ModelControl::StartInit()
{
	_view.AudioPlay(_music);

	int runy = 665;

	_f.SetDir(1);
	_f.SetX(-84);
	_f.SetY(runy);
	_m.SetDir(1);
	_m.SetX(-184);
	_m.SetY(runy);
	_b.SetDir(1);
	_b.SetX(-284);
	_b.SetY(runy + 12);
	_g.SetDir(1);
	_g.SetX(-384);
	_g.SetY(runy + 12);
	_r.SetDir(1);
	_r.SetX(-484);
	_r.SetY(runy + 12);
	_y.SetDir(1);
	_y.SetX(-584);
	_y.SetY(runy + 12);

	_f.SetFrameCount(0);
	_f.SetCurFrame(0);
	_m.SetFrameCount(0);
	_m.SetCurFrame(1);
	_b.SetFrameCount(0);
	_b.SetCurFrame(0);
	_g.SetFrameCount(0);
	_g.SetCurFrame(1);
	_r.SetFrameCount(0);
	_r.SetCurFrame(2);
	_y.SetFrameCount(0);
	_y.SetCurFrame(3);
}

void ModelControl::P1PickInit()
{
	int standy = 250;
	_f.SetDir(1);
	_f.SetX(149);
	_f.SetY(standy);
	_m.SetDir(1);
	_m.SetX(869);
	_m.SetY(standy);
}

void ModelControl::P2PickInit()
{
	int standy = 320;
	_b.SetDir(1);
	_b.SetX(101);
	_b.SetY(standy);
	_g.SetDir(1);
	_g.SetX(381);
	_g.SetY(standy);
	_r.SetDir(1);
	_r.SetX(661);
	_r.SetY(standy);
	_y.SetDir(1);
	_y.SetX(941);
	_y.SetY(standy);
}

void ModelControl::MazeInit()
{
	_view.AudioStop();

	//Countdown();

	int pstartX = 900; // 30
	int pstartY = 200; // 40
	int gstartX = 930;
	int gstartY = 245;

	_sprites[0]->SetDir(1);
	_sprites[0]->SetX(pstartX);
	_sprites[0]->SetY(pstartY);
	_sprites[1]->SetDir(0);
	_sprites[1]->SetX(gstartX);
	_sprites[1]->SetY(gstartY);
	_sprites[2]->SetDir(1);
	_sprites[2]->SetX(gstartX + 50);
	_sprites[2]->SetY(gstartY);
	_sprites[3]->SetDir(0);
	_sprites[3]->SetX(gstartX);
	_sprites[3]->SetY(gstartY + 50);
	_sprites[4]->SetDir(1);
	_sprites[4]->SetX(gstartX + 50);
	_sprites[4]->SetY(gstartY + 50);

	for (auto player : _sprites)
	{
		player->SetFrameCount(0);
		player->SetCurFrame(0);
	}
	
	_view.AudioPlay(_chase);

	_running = true;
}

void MouseObserver::Update()
{
	EventType action = _view.CurrentEvent();

	switch (action)
	{
		case EV_MOUSE_UP:
 			_mc.Click();
			break;
	}

	_mc.Draw();
}

void KeyboardObserver::Update()
{
	EventType action = _view.CurrentEvent();

	switch (action)
	{
		case EV_SPACE:
			_mc.Next();
	}
}

void P1KeyboardObserver::Update()
{
	EventType action = _view.CurrentEvent();

	switch (action)
	{
		case EV_UP:
			_mc.Move(0, EV_UP);
			return;
		case EV_DOWN:
			_mc.Move(0, EV_DOWN);
			return;
		case EV_LEFT:
			_mc.Move(0, EV_LEFT);
			return;
		case EV_RIGHT:
			_mc.Move(0, EV_RIGHT);
			return;
	}
}

void P2KeyboardObserver::Update()
{
	EventType action = _view.CurrentEvent();

	switch (action)
	{
		case EV_A:
			_mc.Move(1, EV_LEFT);
			return;
		case EV_S:
			_mc.Move(1, EV_DOWN);
			return;
		case EV_D:
			_mc.Move(1, EV_RIGHT);
			return;
		case EV_W:
			_mc.Move(1, EV_UP);
			return;
	}
}
#endif