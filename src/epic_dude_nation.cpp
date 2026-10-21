#include "nation.cpp"

nation getEpicDudeNation() {
	nation country;

	// NATIONAL UNITY
	country.b_m.national_unity.population = 61210871.0f;
	country.b_m.national_unity.unrest = -1;
	country.b_m.national_unity.war_support = 0.65;
	country.b_m.national_unity.stability = 0.90;
	country.b_m.national_unity.nationalism = 0.2;
	country.b_m.national_unity.religious_fervor = 0.075;
	country.b_m.national_unity.ideological_radicality = 0;

	// ADMINISTRATION
	country.b_m.administration.autonomy_modifier = 0.7;
	country.b_m.administration.political_power_modifier = 0.80;
	country.b_m.administration.administrative_efficiency = 1.00;
	country.b_m.administration.governing_capacity = 1.1;
	country.b_m.administration.governing_capacity_used = 0;
	country.b_m.administration.corruption = -0.1;
	country.b_m.administration.centralization = 50;
	country.b_m.administration.core_creation_cost = 0.9;

	// DIPLOMACY
	country.b_m.diplomacy.province_warscore_cost = 1;
	country.b_m.diplomacy.diplomatic_capacity = 1; // 2 + 2
	country.b_m.diplomacy.fabricate_claims_cost = 1.2;

	// RESEARCH
	country.b_m.research.research_speed = 1.05;
	country.b_m.research.research_cost = 1.4;

	// ECONOMICS
	country.b_m.economics.income = 0;
	country.b_m.economics.net = 0;
	country.b_m.economics.nd_expenses = 0;
	country.b_m.economics.misc_expenses = 0;
	country.b_m.economics.global_goods_produced_modifier = 1.15;
	country.b_m.economics.national_taxable_base = 0.5;
	country.b_m.economics.national_tax_modifier = 1.1;
	country.b_m.economics.inflation = 0.0;
	country.b_m.economics.global_cost_modifier = 1.0;
	country.b_m.economics.building_cost_modifier = 1.3;
	country.b_m.economics.state_maintenance_modifier = -0.1;

	// MILITARY
	country.b_m.military.recruitable_population = 0.02; // 0.02 + 0
	country.b_m.military.recruitable_population_modifier = 1;
	country.b_m.military.manpower = 0;
	country.b_m.military.casualties = 0;
	country.b_m.military.regiment_upkeep_cost = 1;
	country.b_m.military.land_force_limit = 0;
	country.b_m.military.army_discipline = 1;
	country.b_m.military.army_attack = 1;
	country.b_m.military.core_army_attack = 1;
	country.b_m.military.army_defense = 1;
	country.b_m.military.core_army_defense = 1.3;
	country.b_m.military.army_organization = 1;
	country.b_m.military.army_health = 1;
	country.b_m.military.army_movement_speed = 1;
	country.b_m.military.navy_attack = 1;
	country.b_m.military.navy_defense = 1;
	country.b_m.military.navy_force_limit = 0;
	country.b_m.military.air_attack = 1;

	// GOODS - PRODUCTION
	country.b_m.goods.raw_produced = 25;
	country.b_m.goods.processed_produced = 2;
	country.b_m.goods.advanced_produced = 2;
	country.b_m.goods.food_produced = 600;
	country.b_m.goods.oil_produced = 4;

	// GOODS - CONSUMPTION
	country.b_m.goods.raw_consumed = 3;
	country.b_m.goods.processed_consumed = 0;
	country.b_m.goods.advanced_consumed = 0;
	country.b_m.goods.food_consumed = -20;
	country.b_m.goods.oil_consumed = 0;

	// GOODS - NET BALANCE
	country.b_m.goods.raw = 0;
	country.b_m.goods.processed = 0;
	country.b_m.goods.advanced = 0;
	country.b_m.goods.food = 0;
	country.b_m.goods.oil = 0;

	// Calculate final stats
	country.setupMods();

	return country;
}
