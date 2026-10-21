#pragma once
#include <iomanip>
#include <iostream>
#include <string>

struct NationalUnity {
	float population = 0.0f;
	float unrest = 0.0f;
	float war_support = 0.0f;
	float stability = 0.0f;
	float nationalism = 0.0f;
	float religious_fervor = 0.0f;
	float ideological_radicality = 0.0f;
};

struct Administration {
	float autonomy_modifier = 0.0f;
	float political_power_modifier = 0.0f;
	float administrative_efficiency = 0.0f;
	float governing_capacity = 0.0f;
	float governing_capacity_used = 0.0f;
	float corruption = 0.0f;
	float centralization = 0.0f;
	float core_creation_cost = 0.0f;
};

struct Diplomacy {
	float province_warscore_cost = 0.0f;
	float diplomatic_capacity = 0.0f;
	float fabricate_claims_cost = 0.0f;
};

struct Research {
	float research_speed = 0.0f;
	float research_cost = 0.0f;
};
struct Goods {
	float raw_produced = 0.0f;
	float processed_produced = 0.0f;
	float advanced_produced = 0.0f;
	float food_produced = 0.0f;
	float oil_produced = 0.0f;

	float raw_consumed = 0.0f;
	float processed_consumed = 0.0f;
	float advanced_consumed = 0.0f;
	float food_consumed = 0.0f;
	float oil_consumed = 0.0f;

	float raw = 0.0f;
	float processed = 0.0f;
	float advanced = 0.0f;
	float food = 0.0f;
	float oil = 0.0f;
};

struct Economics {
	float income = 0.0f;
	float net = 0.0f;
	float nd_expenses = 0.0f;
	float misc_expenses = 0.0f;

	float global_goods_produced_modifier = 0.0f;
	float national_taxable_base = 0.0f;
	float national_tax_modifier = 0.0f;
	float inflation = 0.0f;
	float global_cost_modifier = 0.0f;
	float building_cost_modifier = 0.0f;
	float state_maintenance_modifier = 0.0f;
};

struct Military {
	float recruitable_population = 0.0f;
	float recruitable_population_modifier = 0.0f;
	float manpower = 0.0f;
	float casualties = 0.0f;
	float regiment_upkeep_cost = 0.0f;
	float land_force_limit = 0.0f;
	float army_discipline = 0.0f;
	float army_attack = 0.0f;
	float core_army_attack = 0.0f;
	float army_defense = 0.0f;
	float core_army_defense = 0.0f;
	float army_organization = 0.0f;
	float army_health = 0.0f;
	float army_movement_speed = 0.0f;

	float navy_attack = 0.0f;
	float navy_defense = 0.0f;
	float navy_force_limit = 0.0f;

	float air_attack = 0.0f;
};
struct CountryModifiers {
	NationalUnity national_unity;
	Administration administration;
	Diplomacy diplomacy;
	Research research;
	Economics economics;
	Military military;
	Goods goods;
};

struct nation {
	CountryModifiers m;
	CountryModifiers b_m;
	void setupMods() {
		m.national_unity.population = b_m.national_unity.population;
		m.diplomacy.diplomatic_capacity = b_m.diplomacy.diplomatic_capacity;

		m.administration.corruption =
		    std::max(b_m.administration.corruption, 0.0f);
		m.administration.centralization = b_m.administration.centralization;
		m.administration.governing_capacity =
		    50 * b_m.administration.governing_capacity;
		m.administration.governing_capacity_used =
		    m.national_unity.population / 1000000;
		m.national_unity.nationalism =
		    std::max(b_m.national_unity.nationalism, 0.0f);
		m.national_unity.religious_fervor =
		    std::max(b_m.national_unity.religious_fervor, 0.0f);
		m.national_unity.ideological_radicality =
		    std::max(b_m.national_unity.ideological_radicality, 0.0f);
		float maxExtreme =
		    std::max(std::max(m.national_unity.ideological_radicality,
			                  m.national_unity.nationalism),
			         m.national_unity.religious_fervor);

		float governing_efficiency =
		    std::min((m.administration.governing_capacity /
			          b_m.administration.governing_capacity_used),
			         2.0f); // BIGGER IS BETTER
		m.administration.administrative_efficiency =
		    (b_m.administration.administrative_efficiency *
			 std::min(((1 + governing_efficiency) / 2), 1.25f)) *
		        (1 / (m.administration.corruption + 1)) +
		    (m.administration.centralization / 300); // BIGGER IS BETTER
		m.national_unity.stability = std::min(
		    (b_m.national_unity.stability +
			 (b_m.national_unity.unrest * -0.1f) + (maxExtreme / 10.0f)),
		    1.0f);
		m.national_unity.war_support =
		    b_m.national_unity.war_support +
		    b_m.national_unity.nationalism / 0.5 +
		    b_m.national_unity.religious_fervor / 0.75 +
		    b_m.national_unity.ideological_radicality / 0.75;
		m.administration.autonomy_modifier = std::min(
		    std::max(
		        ((b_m.administration.autonomy_modifier + 0.4f) -
				 ((governing_efficiency > 1)
		              ? 0
		              : 1 / (governing_efficiency * governing_efficiency))),
		        0.0f),
		    0.95f);
		m.administration.political_power_modifier =
		    b_m.administration.political_power_modifier *
		    ((1.5 + std::max(m.national_unity.nationalism,
			                 std::max(m.national_unity.ideological_radicality,
			                          m.national_unity.religious_fervor))) /
			 2) *
		    ((2 + m.national_unity.stability) / 2);
		m.administration.core_creation_cost =
		    b_m.administration.core_creation_cost *
		    (1 / m.administration.administrative_efficiency) *
		    (1.25 - (m.national_unity.stability / 2));

		// Diplomacy Mains
		m.diplomacy.province_warscore_cost =
		    b_m.diplomacy.province_warscore_cost * (1 / governing_efficiency);
		m.diplomacy.fabricate_claims_cost =
		    b_m.diplomacy.fabricate_claims_cost *
		    (1.5 - m.national_unity.war_support);

		// Research
		m.research.research_cost = b_m.research.research_cost *
		                           (1 + m.national_unity.religious_fervor);
		m.research.research_speed = b_m.research.research_speed;

		// Unrest
		m.national_unity.unrest =
		    b_m.national_unity.unrest + m.administration.corruption;

		// Economics
		m.economics.inflation = std::max(
		    b_m.economics.inflation + m.administration.corruption, 0.0f);
		m.economics.building_cost_modifier =
		    b_m.economics.building_cost_modifier;
		m.economics.global_cost_modifier =
		    b_m.economics.global_cost_modifier * (1 + m.economics.inflation);
		m.economics.national_taxable_base =
		    b_m.economics.national_taxable_base *
		    (1 + m.national_unity.nationalism);
		m.economics.national_tax_modifier =
		    b_m.economics.national_tax_modifier *
		    std::min(m.administration.administrative_efficiency, 1.2f) *
		    (1 - m.administration.autonomy_modifier);
		m.economics.global_goods_produced_modifier =
		    b_m.economics.global_goods_produced_modifier *
		    (1 - m.administration.autonomy_modifier) * ((2 + maxExtreme) / 2);
		m.economics.state_maintenance_modifier =
		    std::max(b_m.economics.state_maintenance_modifier *
			             (1 + m.economics.inflation),
			         0.05f);

		m.economics.misc_expenses = b_m.economics.misc_expenses;
		m.economics.nd_expenses = m.administration.governing_capacity_used *
		                          m.economics.state_maintenance_modifier *
		                          m.economics.global_cost_modifier;
		m.economics.income = m.economics.national_taxable_base *
		                     m.administration.governing_capacity_used *
		                     m.economics.national_tax_modifier;
		m.economics.net = m.economics.income - m.economics.nd_expenses -
		                  m.economics.misc_expenses;

		// RESOURCES
		m.goods.advanced_consumed =
		    b_m.goods.advanced_consumed * (1 + m.administration.corruption);
		m.goods.processed_consumed =
		    b_m.goods.processed_consumed * (1 + m.administration.corruption);
		m.goods.food_consumed = (b_m.goods.food_consumed +
		                         m.administration.governing_capacity_used) *
		                        (1 + m.administration.corruption);
		m.goods.oil_consumed =
		    b_m.goods.oil_consumed * (1 + m.administration.corruption);
		m.goods.raw_consumed =
		    b_m.goods.raw_consumed * (1 + m.administration.corruption);

		m.goods.advanced_produced = b_m.goods.advanced_produced *
		                            m.economics.global_goods_produced_modifier;
		m.goods.processed_produced = b_m.goods.processed_produced *
		                             m.economics.global_goods_produced_modifier;
		m.goods.food_produced = b_m.goods.food_produced *
		                        m.economics.global_goods_produced_modifier;
		m.goods.oil_produced =
		    b_m.goods.oil_produced * m.economics.global_goods_produced_modifier;
		m.goods.raw_produced =
		    b_m.goods.raw_produced * m.economics.global_goods_produced_modifier;

		m.goods.advanced =
		    m.goods.advanced_produced - m.goods.advanced_consumed;
		m.goods.raw = m.goods.raw_produced - m.goods.raw_consumed;
		m.goods.processed =
		    m.goods.processed_produced - m.goods.processed_consumed;
		m.goods.food = m.goods.food_produced - m.goods.food_consumed;
		m.goods.oil = m.goods.oil_produced - m.goods.oil_consumed;

		m.military.navy_force_limit =
		    m.administration.governing_capacity_used *
		    m.administration.administrative_efficiency / 2;
		m.military.casualties = b_m.military.casualties;
		m.military.air_attack =
		    b_m.military.air_attack * ((1 + maxExtreme) / 2);
		m.military.army_attack =
		    b_m.military.army_attack * ((2 + maxExtreme) / 2);
		m.military.army_discipline = b_m.military.army_discipline;
		m.military.core_army_attack = b_m.military.core_army_attack;
		m.military.army_defense = b_m.military.army_defense;

		m.military.core_army_defense = b_m.military.core_army_defense;
		m.military.army_health = b_m.military.army_health;
		m.military.army_movement_speed = b_m.military.army_movement_speed;
		m.military.land_force_limit =
		    m.administration.governing_capacity_used *
		    m.administration.administrative_efficiency;
		m.military.recruitable_population_modifier =
		    b_m.military.recruitable_population_modifier *
		    ((3 + m.national_unity.war_support) / 3);
		m.military.recruitable_population = b_m.military.recruitable_population;
		m.military.manpower =
		    (m.military.recruitable_population * m.national_unity.population) *
		        m.military.recruitable_population_modifier -
		    m.military.casualties;
		m.military.navy_attack =
		    b_m.military.navy_attack * ((3 + maxExtreme) / 3);
		m.military.navy_defense =
		    b_m.military.navy_defense * ((3 + maxExtreme) / 3);
		m.military.regiment_upkeep_cost = b_m.military.regiment_upkeep_cost *
		                                  m.economics.global_cost_modifier;
	}

	// Units
};

void printNationStats(const nation& n) {
	const auto& m = n.m;

	auto header = [](const std::string& name) {
		std::cout << "\n  " << name << "\n";
		std::cout << "  " << std::string(48, '-') << "\n";
	};

	auto stat = [](const std::string& name, float value, bool percent = false) {
		std::cout << "  " << std::left << std::setw(34) << name << std::right
		          << std::fixed << std::setprecision(2);

		if (percent)
			std::cout << std::setw(12) << value * 100 << "%\n";
		else
			std::cout << std::setw(12) << value << "\n";
	};

	std::cout << "\n";
	std::cout
	    << "============================================================\n";
	std::cout << "                      NATION STATS\n";
	std::cout
	    << "============================================================\n";

	// NATIONAL UNITY
	header("NATIONAL UNITY");
	const auto& u = m.national_unity;
	stat("Population", u.population);
	stat("Unrest", u.unrest, false);
	stat("War Support", u.war_support, true);
	stat("Stability", u.stability, true);
	stat("Nationalism", u.nationalism, true);
	stat("Religious Fervor", u.religious_fervor, true);
	stat("Ideological Radicality", u.ideological_radicality, true);

	// ADMINISTRATION
	header("ADMINISTRATION");
	const auto& a = m.administration;
	stat("Autonomy Modifier", a.autonomy_modifier, true);
	stat("Political Power Modifier", a.political_power_modifier, true);
	stat("Administrative Efficiency", a.administrative_efficiency, false);
	stat("Governing Capacity", a.governing_capacity);
	stat("Governing Capacity Used", a.governing_capacity_used);
	stat("Corruption", a.corruption, true);
	stat("Centralization", a.centralization);
	stat("Core Creation Cost", a.core_creation_cost, true);

	// DIPLOMACY
	header("DIPLOMACY");
	const auto& d = m.diplomacy;
	stat("Province Warscore Cost", d.province_warscore_cost, true);
	stat("Diplomatic Capacity", d.diplomatic_capacity);
	stat("Fabricate Claims Cost", d.fabricate_claims_cost, true);

	// RESEARCH
	header("RESEARCH");
	const auto& r = m.research;
	stat("Research Speed", r.research_speed, true);
	stat("Research Cost", r.research_cost, true);

	// ECONOMICS
	header("ECONOMICS");
	const auto& e = m.economics;
	stat("Income", e.income);
	stat("Net Income", e.net);
	stat("National Expenses", e.nd_expenses);
	stat("Misc Expenses", e.misc_expenses);
	stat("Global Goods Produced Modifier",
	     e.global_goods_produced_modifier,
	     true);
	stat("National Taxable Base", e.national_taxable_base);
	stat("National Tax Modifier", e.national_tax_modifier, true);
	stat("Inflation", e.inflation, true);
	stat("Global Cost Modifier", e.global_cost_modifier, true);
	stat("Building Cost Modifier", e.building_cost_modifier, true);
	stat("State Maintenance Modifier", e.state_maintenance_modifier, true);

	// MILITARY
	header("MILITARY");
	const auto& mil = m.military;
	stat("Recruitable Population", mil.recruitable_population, true);
	stat("Recruitable Population Modifier",
	     mil.recruitable_population_modifier,
	     true);
	stat("Manpower", mil.manpower);
	stat("Casualties", mil.casualties);
	stat("Regiment Upkeep Cost", mil.regiment_upkeep_cost);
	stat("Land Force Limit", mil.land_force_limit);
	stat("Army Discipline", mil.army_discipline, true);
	stat("Army Attack", mil.army_attack);
	stat("Core Army Attack", mil.core_army_attack);
	stat("Army Defense", mil.army_defense);
	stat("Core Army Defense", mil.core_army_defense);
	stat("Army Organization", mil.army_organization, true);
	stat("Army Health", mil.army_health);
	stat("Army Movement Speed", mil.army_movement_speed);
	stat("Navy Attack", mil.navy_attack);
	stat("Navy Defense", mil.navy_defense);
	stat("Navy Force Limit", mil.navy_force_limit);
	stat("Air Attack", mil.air_attack);

	// GOODS
	header("GOODS - PRODUCTION");
	const auto& g = m.goods;
	stat("Raw Produced", g.raw_produced);
	stat("Processed Produced", g.processed_produced);
	stat("Advanced Produced", g.advanced_produced);
	stat("Food Produced", g.food_produced);
	stat("Oil Produced", g.oil_produced);

	header("GOODS - CONSUMPTION");
	stat("Raw Consumed", g.raw_consumed);
	stat("Processed Consumed", g.processed_consumed);
	stat("Advanced Consumed", g.advanced_consumed);
	stat("Food Consumed", g.food_consumed);
	stat("Oil Consumed", g.oil_consumed);

	header("GOODS - NET BALANCE");
	stat("Raw", g.raw);
	stat("Processed", g.processed);
	stat("Advanced", g.advanced);
	stat("Food", g.food);
	stat("Oil", g.oil);

	std::cout
	    << "\n============================================================\n";
}