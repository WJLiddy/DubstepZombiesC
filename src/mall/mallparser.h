#ifndef MALL_PARSER_H
#define MALL_PARSER_H
class MallParser
{
private:
	// Base, Always, Map Object List, Collide layer, Map Object List
	MallParser(ALLEGRO_BITMAP*, ALLEGRO_BITMAP*, std::set<Coord>; std::vector<MallObject>);
public:
	MallParser parse(std::string);
	MallDraw mallDraw();
	std::vector<MallObject> mallObjects();
	std::set<Coord> collide();
}
#endif