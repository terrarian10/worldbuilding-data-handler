#include "nation.cpp"

nation getKyrakan() {
	nation kyrakan;

	// NATIONAL UNITY
	kyrakan.b_m.national_unity.population = 25311415.0f;
	kyrakan.b_m.national_unity.unrest = -3.5;
	kyrakan.b_m.national_unity.war_support = 0.50;
	kyrakan.b_m.national_unity.stability = 0.10;
	kyrakan.b_m.national_unity.nationalism = -0.1;
	kyrakan.b_m.national_unity.religious_fervor = 0;
	kyrakan.b_m.national_unity.ideological_radicality = 0.3;

	// ADMINISTRATION
	kyrakan.b_m.administration.autonomy_modifier = -0.3;
	kyrakan.b_m.administration.political_power_modifier = 0.60;
	kyrakan.b_m.administration.administrative_efficiency = 1.05;
	kyrakan.b_m.administration.governing_capacity = 0.55;
	kyrakan.b_m.administration.governing_capacity_used = 0;
	kyrakan.b_m.administration.corruption = -0.1;
	kyrakan.b_m.administration.centralization = 25;
	kyrakan.b_m.administration.core_creation_cost = 1.50;

	// DIPLOMACY
	kyrakan.b_m.diplomacy.province_warscore_cost = 1;
	kyrakan.b_m.diplomacy.diplomatic_capacity = 4; // 2 + 2
	kyrakan.b_m.diplomacy.fabricate_claims_cost = 1;

	// RESEARCH
	kyrakan.b_m.research.research_speed = 1.8;
	kyrakan.b_m.research.research_cost = 1;

	// ECONOMICS
	kyrakan.b_m.economics.income = 0;
	kyrakan.b_m.economics.net = 0;
	kyrakan.b_m.economics.nd_expenses = 0;
	kyrakan.b_m.economics.misc_expenses = 0;
	kyrakan.b_m.economics.global_goods_produced_modifier = 1.35;
	kyrakan.b_m.economics.national_taxable_base = 1;
	kyrakan.b_m.economics.national_tax_modifier = 1.6;
	kyrakan.b_m.economics.inflation = -0.05;
	kyrakan.b_m.economics.global_cost_modifier = 0.95;
	kyrakan.b_m.economics.building_cost_modifier = 1;
	kyrakan.b_m.economics.state_maintenance_modifier = 1.55;

	// MILITARY
	kyrakan.b_m.military.recruitable_population = 0.02; // 0.02 + 0
	kyrakan.b_m.military.recruitable_population_modifier = 1;
	kyrakan.b_m.military.manpower = 0;
	kyrakan.b_m.military.casualties = 0;
	kyrakan.b_m.military.regiment_upkeep_cost = 1;
	kyrakan.b_m.military.land_force_limit = 0;
	kyrakan.b_m.military.army_discipline = 1;
	kyrakan.b_m.military.army_attack = 1;
	kyrakan.b_m.military.core_army_attack = 1;
	kyrakan.b_m.military.army_defense = 1;
	kyrakan.b_m.military.core_army_defense = 1;
	kyrakan.b_m.military.army_organization = 1;
	kyrakan.b_m.military.army_health = 1;
	kyrakan.b_m.military.army_movement_speed = 1;
	kyrakan.b_m.military.navy_attack = 1;
	kyrakan.b_m.military.navy_defense = 1;
	kyrakan.b_m.military.navy_force_limit = 0;
	kyrakan.b_m.military.air_attack = 1;

	// GOODS - PRODUCTION
	kyrakan.b_m.goods.raw_produced = 30;
	kyrakan.b_m.goods.processed_produced = 15;
	kyrakan.b_m.goods.advanced_produced = 10;
	kyrakan.b_m.goods.food_produced = 25;
	kyrakan.b_m.goods.oil_produced = 5;

	// GOODS - CONSUMPTION
	kyrakan.b_m.goods.raw_consumed = 20;
	kyrakan.b_m.goods.processed_consumed = 5;
	kyrakan.b_m.goods.advanced_consumed = 0;
	kyrakan.b_m.goods.food_consumed = 0;
	kyrakan.b_m.goods.oil_consumed = 2;

	// GOODS - NET BALANCE
	kyrakan.b_m.goods.raw = 0;
	kyrakan.b_m.goods.processed = 0;
	kyrakan.b_m.goods.advanced = 0;
	kyrakan.b_m.goods.food = 0;
	kyrakan.b_m.goods.oil = 0;

	// Calculate final stats
	kyrakan.setupMods();

	return kyrakan;
}
